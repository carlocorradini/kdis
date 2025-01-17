# KDIS

[![release](https://github.com/karljj1/kdis/actions/workflows/release.yaml/badge.svg)](https://github.com/karljj1/kdis/actions/workflows/release.yaml)
[![codeql](https://github.com/karljj1/kdis/actions/workflows/codeql.yaml/badge.svg)](https://github.com/karljj1/kdis/actions/workflows/codeql.yaml)

Open source implementation of `DIS` (_Distributed Interactive Simulation_) `IEEE 1278.1`

## Contributing

I would love to see your contribution :heart:

See [CONTRIBUTING](./CONTRIBUTING.md) guidelines

## Development

### Requirements

| **Name**       | **Homepage**                                   |    **Required**    | **Notes**                                                                                                         |
| -------------- | ---------------------------------------------- | :----------------: | ----------------------------------------------------------------------------------------------------------------- |
| `CXX Compiler` |                                                | :heavy_check_mark: | [`GCC`](https://gcc.gnu.org) \| [`Clang`](https://clang.llvm.org) \| [`MSVC`](https://visualstudio.microsoft.com) |
| `CMake`        | <https://cmake.org>                            | :heavy_check_mark: | _Version `>= 3.14`_                                                                                               |
| `Clang Format` | <https://clang.llvm.org/docs/ClangFormat.html> |        :x:         |
| `Clang Tidy`   | <https://clang.llvm.org/extra/clang-tidy>      |        :x:         |
| `Cppcheck`     | <https://github.com/danmar/cppcheck>           |        :x:         |
| `Cpplint`      | <https://github.com/cpplint/cpplint>           |        :x:         | `pip install cpplint`                                                                                             |
| `cmake lang`   | <https://github.com/cheshirekow/cmake_format>  |        :x:         | `pip install cmakelang[YAML]`                                                                                     |
| `Doxygen`      | <https://www.doxygen.nl>                       |        :x:         | Documentation                                                                                                     |

### Build Options

| **Name**                    | **Description**                                                                                                                                      | **Type** | **Default** |
| --------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- | -------- | ----------- |
| `DIS_VERSION`               | `DIS` version: <br/> <ul><li>`5`<br/>_IEEE 1278.1-1995_</li><li>`6`<br/>_IEEE 1278.1A-1998_</li><li>`7`<br/>_IEEE 1278.1x-2012_</li></ul>            | `STRING` | `7`         |
| `KDIS_USE_ENUM_DESCRIPTORS` | Enumeration descriptors. <br/> Allow `enum` values to be turned into their text labels. <br/> :warning: Increase the memory footprint of the library | `BOOL`   | `TRUE`      |
| `KDIS_BUILD_DOCS`           | Build documentation                                                                                                                                  | `BOOL`   | `FALSE`     |
| `KDIS_BUILD_EXAMPLES`       | Build examples                                                                                                                                       | `BOOL`   | `FALSE`     |
| `KDIS_BUILD_TESTS`          | Build tests                                                                                                                                          | `BOOL`   | `FALSE`     |
| `BUILD_SHARED_LIBS`         | Build shared library                                                                                                                                 | `BOOL`   | `TRUE`      |

### Build

1. Generate project

    > [!NOTE]
    > Change build options' values as needed

    ```sh
    cmake \
        -S . \
        -B ./build \
        -DCMAKE_BUILD_TYPE:STRING=Release \
        -DDIS_VERSION:STRING=7 \
        -DKDIS_USE_ENUM_DESCRIPTORS:BOOL=TRUE \
        -DBUILD_SHARED_LIBS:BOOL=TRUE \
        -DKDIS_BUILD_DOCS:BOOL=FALSE \
        -DKDIS_BUILD_EXAMPLES:BOOL=FALSE \
        -DKDIS_BUILD_TESTS:BOOL=FALSE
    ```

1. Build project

    > [!NOTE]
    > Change value of `--config` to match value of `CMAKE_BUILD_TYPE`

    ```sh
    cmake \
        --build ./build \
        --config Release
    ```

## Documentation

> [!IMPORTANT]
> `KDIS_BUILD_DOCS:BOOL=TRUE` required

File `index.html` available under [`build/docs/html`](./build/docs/html) directory

More information can be found in [`docs/README.md`](./docs/README.md)

## Examples

> [!IMPORTANT]
> `KDIS_BUILD_EXAMPLES:BOOL=TRUE` required

More information can be found in [`examples/README.md`](./examples/README.md)

## Scripts

More information can be found in [`scripts/README.md`](./scripts/README.md)

## Tests

> [!IMPORTANT]
> `KDIS_BUILD_TESTS:BOOL=TRUE` required

> [!NOTE]
> Change value of `--build-config` to match value of `CMAKE_BUILD_TYPE`

```sh
ctest \
    --verbose \
    --test-dir ./build/tests \
    --build-config Release
```

More information can be found in [`tests/README.md`](./tests/README.md)

## License

This project is licensed under the [BSD 2-Clause](https://opensource.org/license/bsd-2-clause) "Simplified" License \
See [LICENSE](./LICENSE) file for details
