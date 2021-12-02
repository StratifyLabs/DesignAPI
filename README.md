# LibraryAPI

This is a template for creating a new API style library. Don't bother trying to build it. It wont' build. To use it, you need to create a new project using this project as the template. You then change `LibraryAPI` to the name of your API library within the cmake and source files as needed. You can add API-style dependencies or an external project depependency. For examples on how those work, please see these repos:

- [JsonAPI](https://github.com/StratifyLabs/JsonAPI): builds [jansson JSON library](https://github.com/akheron/jansson) as a sub-project
- [InetAPI](https://github.com/StratifyLabs/InetAPI): builds [mbedtls](https://github.com/ARMmbed/mbedtls) and [lwip](https://github.com/StratifyLabs/StratifyOS-lwip) as subprojects
- [WindowAPI](https://github.com/StratifyLabs/WindowAPI): builds [libsdl](https://github.com/libsdl-org) as an external project dependency

This project is designed to be pulled and built as part of a super project such as:

- [cli](https://github.com/StratifyLabs/cli)
- [gui](https://github.com/StratifyLabs/gui)
- [STM32H735G-DK](https://github.com/StratifyLabs/STM32H735G-DK)
