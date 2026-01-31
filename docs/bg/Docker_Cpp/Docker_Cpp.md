# Docker и C++ Разработка - Пълно техническо ръководство

## 1. Въведение: Защо контейнери за нативен код?

В света на уеб разработката (Java, Python, Node.js), Docker е стандарт. В C++ света обаче, приемането му е по-бавно. Защо? Защото C++ е нативен език. Той се компилира директно за хардуера и операционната система.
Проблемът "Работи на моята машина" обаче е най-остър именно при C++.
*   "Аз съм с GCC 9, ти си с GCC 11."
*   "Аз инсталирах Boost 1.70 през apt, ти ползваш 1.81."
*   "Аз съм на Arch Linux, ти си на Ubuntu 18.04."

Docker решава това кардинално. Той капсулира цялата "вселена" на проекта – компилатор, билд система (CMake/Ninja), библиотеки и конфигурации – в един преносим пакет. Това гарантира, че компилацията е детерминистична.

---

## 2. Multi-Stage Builds: Изкуството на оптимизацията

C++ компилацията генерира огромни междинни файлове (`.o`, `.a`) и изисква тежки инструменти (хедъри, компилатори, дебъгери), които не са нужни на крайния потребител.
**Multi-stage builds** е техниката, с която разделяме процеса на две фази:
1.  **Builder:** Тежък имидж с всички инструменти. Тук компилираме кода.
2.  **Runtime:** Минималистичен имидж (напр. Alpine или Debian Slim), в който копираме САМО готовото бинарно приложение.

```dockerfile
# Етап 1: Build Environment
# Използваме пълен Ubuntu имидж с всички инструменти
FROM ubuntu:22.04 AS builder

# Инсталиране на компилатор и библиотеки (кеширан слой)
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    libssl-dev

WORKDIR /app

# Копираме първо само файловете за зависимости (за по-добър кеш)
COPY CMakeLists.txt vcpkg.json ./

# Копираме целия сорс код
COPY . .

# Компилация (Release mode)
RUN mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTS=OFF && \
    make -j$(nproc)

# Етап 2: Runtime Environment
# Използваме олекотен имидж за продукция
FROM ubuntu:22.04 AS runtime

# Инсталираме само runtime библиотеките (без хедъри и компилатори)
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    libssl3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Копираме САМО изпълнимия файл от предния етап
COPY --from=builder /app/build/my_awesome_app .
COPY --from=builder /app/config.json .

# Стартиране
CMD ["./my_awesome_app"]
```
Резултатът е имидж с размер 50MB, вместо 2GB.

---

## 3. Alpine Linux vs Debian/Ubuntu

Много C++ програмисти се изкушават да ползват **Alpine Linux** за runtime, защото е само 5MB.
Трябва да сте много внимателни с това.
*   **glibc vs musl:** Стандартните Linux дистрибуции (Debian, Ubuntu, Fedora) използват GNU C Library (`glibc`). Alpine използва `musl libc`.
*   **Съвместимост:** C++ кодът обикновено е съвместим, но някои ниско-нивови оптимизации или специфични библиотеки може да не работят или да се държат различно (напр. DNS resolution, Thread stack size).
*   **Performance:** `glibc` често е по-бърза за тежки изчисления (заради SIMD оптимизации), докато `musl` е оптимизирана за малък размер.

**Препоръка:** За C++ проекти, особено в Enterprise среда, по-безопасният избор е `debian:slim` или `gcr.io/distroless/cc` (Google Distroless), освен ако не сте готови да дебъгвате специфични `musl` проблеми.

---

## 4. Интеграция с CI/CD (GitHub Actions / GitLab CI)

Docker е гръбнакът на модерния CI. Вместо да конфигурирате ръчно агентите (Runner-ите) и да се чудите защо Jenkins билдът фейлва, вие просто казвате: "Билдни този Dockerfile".

### Пример за GitHub Actions Workflow
```yaml
name: C++ CI

on: [push, pull_request]

jobs:
  build:
    runs-on: ubuntu-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Build Docker Image
      run: docker build -t my-app:latest .
      
    - name: Run Tests inside Container
      run: docker run --rm my-app:latest ./run_tests
```
Този подход гарантира, че тестовете се въртят в абсолютно същата среда, в която приложението е било компилирано.

---

## 5. DevContainers: Разработка в контейнер

VS Code и CLion поддържат технологията **DevContainers**.
Това позволява на програмистите да пишат код в IDE-то на своя компютър (дори да е Windows или Mac), но цялата компилация, дебъгване и IntelliSense (автоматично дописване) да вървят вътре в Linux контейнер.
Това елиминира нуждата от Dual-Boot или виртуални машини. Вие получавате пълната мощ на Linux development средата, интегрирана прозрачно.

**Как работи?**
Проектът съдържа папка `.devcontainer` с конфигурация (`devcontainer.json`). Когато отворите проекта, VS Code ви пита "Искате ли да отворите в контейнер?". Ако кажете да, той изгражда Docker имиджа, пуска го и закача IDE-то към него.

---

## 6. Професионални съвети

1.  **Static Linking:** За максимална преносимост и сигурност, обмислете статично свързване (`-static`). Тогава можете да използвате `FROM scratch` (празен имидж) за финалния етап. Вашият контейнер ще съдържа *само* един файл – приложението. Няма OS, няма shell, няма инструменти за хакерите.
2.  **CCache:** Компилацията в Docker може да е бавна, защото всеки `docker build` започва отначало. Използвайте `ccache` и закачете външен Volume, за да запазите кеша между билдовете.
3.  **Cross-Compilation:** Docker е най-лесният начин да компилирате за ARM (напр. Raspberry Pi) на вашата мощна x86 машина, използвайки `docker buildx`.

---
*(Този документ е част от "The Ultimate C++ Mastery Framework".)*