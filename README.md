# ZWSH
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub release](https://img.shields.io/github/v/release/linuxdeveloper6-lang/zwsh-shell)](https://github.com/linuxdeveloper6-lang/zwsh-shell/releases)
![Commits](https://img.shields.io/github/commit-activity/m/linuxdeveloper6-lang/zwsh-shell)
## What is ZWSH?
**ZWSH (Zero Weight SHell)** is a **lightweight** Linux shell.
## Configuration
You can customize the prompt by setting the `ZWSH_PROMPT` environment variable:
```bash
export ZWSH_PROMPT="zwsh> "
```
## Examples
### Start ZWSH
```bash
zwsh
```
### ZWSH utils
```bash
ls
cat
cd
echo
clear
exit
```
**Starts the ZWSH-built-in utils**
## Building from source
### Requirements
- GCC or Clang
- GNU Make
- Readline development library
### Step 1.
**Download** the source.
```bash
git clone https://github.com/linuxdeveloper6-lang/zwsh-shell.git
cd zwsh-shell
```
### Step 2.
**Start** the build.
```bash
make
sudo make install #installing
```
## LICENSE
**See** ![LICENSE](LICENSE)
