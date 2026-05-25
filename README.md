# boson

Project Boson is a lightweight overlay, schedule, and alerts app designed to run without a reliance on third-party intermediary.

# Roadmap

* Quality
    * ✅ Add code coverage [generation](https://github.com/gcovr/gcovr) and [reporting](https://github.com/marketplace/actions/code-coverage-summary).
    * ✅ Add unit tests
    * Add coding and contribution guidelines.
* Integration
    * Add Windows build target
    * Add dependency on SDL 3
    * ✅ Add [JSON parser](https://github.com/nlohmann/json)
    * Add [WebSocket client](https://machinezone.github.io/IXWebSocket/)
    * Add Spout2 library
    * Figure out HTTP requests ((WinINet)[https://learn.microsoft.com/en-us/windows/win32/wininet/portal], (libcurl)[https://curl.se/libcurl/])
* Functionality
    * Add URL handler for Windows, macOS, and Linux build targets.
    * Implement Twitch API redirect flow.
    * Add Twitch EventSub integration
* Milestone 1
    * Twitch authorization flow and WebSocket connection works

# Install dependencies

# macOS/Linux

## vcpkg

Follow the vcpkg setup guide.

```
cd vendor/vcpkg && ./bootstrap-vcpkg.sh
```


# Building

```
cmake --preset=default
cmake -B build
cmake --build build
```

# Running tests

```
cd build
ctest -T Test -T Coverage
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
    sudo apt install -y nlohmann-json3-dev
finch run --volume $PWD:/data --workdir /data \
    registry.gitlab.steamos.cloud/steamrt/steamrt4/sdk \
    cmake -B build
finch run --volume $PWD:/data --workdir /data \
    registry.gitlab.steamos.cloud/steamrt/steamrt4/sdk \
    cmake --build build
````

# Attribution

The placeholder [application icon](https://icons.getbootstrap.com/icons/broadcast-pin/) is from Bootstrap under the MIT License.