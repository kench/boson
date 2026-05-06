# boson
A systems programming sandbox

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