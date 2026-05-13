# boson

Project Boson is a lightweight overlay, schedule, and alerts app designed to run without a reliance on third-party intermediary.

# Roadmap

* Quality
    * Add code coverage [generation](https://github.com/gcovr/gcovr) and [reporting](https://github.com/marketplace/actions/code-coverage-summary).
    * Add unit tests
    * Add coding and contribution guidelines.
* Integration
    * Add Windows build target
    * Add dependency on SDL 3
    * Add [JSON parser](https://github.com/nlohmann/json)
    * Add [WebSocket client](https://machinezone.github.io/IXWebSocket/)
    * Add Spout2 library
    * Figure out HTTP requests ((WinINet)[https://learn.microsoft.com/en-us/windows/win32/wininet/portal], (libcurl)[https://curl.se/libcurl/])
* Functionality
    * Add URL handler for Windows, macOS, and Linux build targets.
    * Implement Twitch API redirect flow.
    * Add Twitch EventSub integration

# Building

```
cmake -B build
cmake --build build
```

# Executing

```
./build/boson
```

# macOS build instructions

Ensure [Finch](https://runfinch.com) is installed first.

```
finch run --volume $PWD:/data --workdir /data \
    registry.gitlab.steamos.cloud/steamrt/steamrt4/sdk \
    cmake -B build
finch run --volume $PWD:/data --workdir /data \
    registry.gitlab.steamos.cloud/steamrt/steamrt4/sdk \
    cmake --build build
````