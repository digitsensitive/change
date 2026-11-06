# Changelog

## [0.0.*] - ****-**-**

### Added
### Changed
### Fixed

---

## [0.0.1] - First Release - 2026-XX-XX

### Added

- [x] Create Texture Manager *2026/11/01*
- [x] Add content field for tiles *2026/11/02*
- [x] Add a basic random spawn function for tile contents *2026/11/02*
- [x] Make the random spawn function for tile contents more flexible, so that
  it works for different content types (f.e. STONES, TREES ...). It should be
  easy to add any future contents *2026/11/06*
- [ ] In the `tm_add` function strip out the full path, only need name
- [ ] Add a `tm_draw` function that calls the `get_texture`

### Changed

- [x] Add own typedef for unsigned int called `uint` *2026/11/01*
- [x] Refactor Island Generator *2026/11/01*

### Fixed

- [x] Fix path for header files when formatting via `make format` *2026/11/01*
- [x] Fix player position after is mouse button down *2026/11/06*
