# AWF - A widget factory (extended)

A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme.

## Screenshots

GTK 2.24 (Pango 1.51)\
[<img alt="Preview with GTK 2 - Main window" src="images/thumbs/gtk2.png?raw=true" width="200" />](images/gtk2.png?raw=true)
[<img alt="Preview with GTK 2 - Menu" src="images/thumbs/gtk2-menu.png?raw=true" width="200" />](images/gtk2-menu.png?raw=true)
[<img alt="Preview with GTK 2 - RTL - Main window" src="images/thumbs/gtk2-rtl.png?raw=true" width="200" />](images/gtk2-rtl.png?raw=true)
[<img alt="Preview with GTK 2 - RTL - Menu" src="images/thumbs/gtk2-rtl-menu.png?raw=true" width="200" />](images/gtk2-rtl-menu.png?raw=true)

GTK 3.24 (Pango 1.51)\
[<img alt="Preview with GTK 3 - Main window" src="images/thumbs/gtk3.png?raw=true" width="200" />](images/gtk3.png?raw=true)
[<img alt="Preview with GTK 3 - Menu" src="images/thumbs/gtk3-menu.png?raw=true" width="200" />](images/gtk3-menu.png?raw=true)
[<img alt="Preview with GTK 3 - RTL - Main window" src="images/thumbs/gtk3-rtl.png?raw=true" width="200" />](images/gtk3-rtl.png?raw=true)
[<img alt="Preview with GTK 3 - RTL - Menu" src="images/thumbs/gtk3-rtl-menu.png?raw=true" width="200" />](images/gtk3-rtl-menu.png?raw=true)

GTK 4.12 (Pango 1.51)\
[<img alt="Preview with GTK 4 - Main window" src="images/thumbs/gtk4.png?raw=true" width="200" />](images/gtk4.png?raw=true)
[<img alt="Preview with GTK 4 - Menu" src="images/thumbs/gtk4-menu.png?raw=true" width="200" />](images/gtk4-menu.png?raw=true)
[<img alt="Preview with GTK 4 - RTL - Main window" src="images/thumbs/gtk4-rtl.png?raw=true" width="200" />](images/gtk4-rtl.png?raw=true)
[<img alt="Preview with GTK 4 - RTL - Menu" src="images/thumbs/gtk4-rtl-menu.png?raw=true" width="200" />](images/gtk4-rtl-menu.png?raw=true)

Theme used for the screenshots is available [here](https://github.com/luigifab/human-theme).

## Tricks

* Some options are available from command line (read `-h` or man page).
* Options menu allow to display some standard dialogs.
* System and user themes menu allow to set current theme.
* Text direction menu allow to change text direction (LTR/RTL).
* Plus/minus toolbar buttons allow to show or hide: notebooks arrows, marks on progress bars and scales...
* Refresh toolbar button and refresh menu item allow to reload the current theme (like `SIGHUP` signal).
* Menu keyboard shortcuts can be updated on hover (GTK 2.24 and 3.x, *gtk-can-change-accels*).
* Notebooks tabs are scrollable (GTK 3.x and 4.x, *gtk-scroll-tabs*, like with GTK 2.24).
* With Ubuntu, menu keyboard shortcuts can also be updated on hover with: `UBUNTU_MENUPROXY= awf-gtk3`

## Installation

It require **GTK 2.24** or **GTK 3.0+** *(including 3.24)* or **GTK 4.0+** *(including 4.17)*, and *GLIB 2.28+*.

#### Installation for Debian, Devuan, Ubuntu, Trisquel, Linux Mint, MX Linux

* `sudo apt install awf-gtk2 awf-gtk3 awf-gtk4`

#### Installation for Fedora

* `sudo dnf install awf-gtk2 awf-gtk3 awf-gtk4`

#### Installation for openSUSE

* `sudo zypper install awf-gtk2 awf-gtk3 awf-gtk4`

#### Installation for Mageia

* `sudo urpmi awf-gtk2 awf-gtk3 awf-gtk4`

#### Building from source

* To compile the program with all available major versions of GTK run: `build.sh`
* To compile the program and create DEB packages for Debian & Ubuntu run: `debian-gtkx/deb.sh`
* To compile the program and create RPM packages for Fedora run: `fedora/rpm-gtkx.sh`
* To compile the program and create RPM packages for openSUSE run: `opensuse/rpm-gtkx.sh`
* To compile the program and create RPM packages for Mageia run: `mageia/rpm-gtkx.sh`

#### Alternative installation for Debian, Devuan, Ubuntu, Trisquel, Linux Mint, MX Linux

```bash
# PPA: https://launchpad.net/~luigifab/+archive/ubuntu/packages
# with Debian 12+ you can use mantic+ instead of focal (https://unix.stackexchange.com/a/669008/364800)
# for Debian you can use bionic for buster, focal for bullseye, noble for bookworm and trixie
# for Devuan you can use bionic for beowulf, focal for chimaera, noble for daedalus
# for Trisquel you can use focal for nabia, jammy for aramo
# for Linux Mint you can use focal for 20.x and 5, jammy for 21.x, noble for 22.x and 6
# for MX Linux you can use focal for 19.x and 21.x, noble for 23.x

sudo add-apt-repository ppa:luigifab/packages
sudo apt update
sudo apt install awf-gtk2 awf-gtk3 awf-gtk4
# or
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys FFE5BD439356DF7D
echo "deb http://ppa.launchpad.net/luigifab/packages/ubuntu focal main" | sudo tee -a /etc/apt/sources.list
sudo apt update
sudo apt install awf-gtk2 awf-gtk3 awf-gtk4
# or
sudo wget -O /etc/apt/trusted.gpg.d/luigifab.gpg https://www.luigifab.fr/apt.gpg
echo "deb http://ppa.launchpad.net/luigifab/packages/ubuntu focal main" | sudo tee -a /etc/apt/sources.list
sudo apt update
sudo apt install awf-gtk2 awf-gtk3 awf-gtk4
# or
wget -qO - https://www.luigifab.fr/apt.gpg | sudo gpg --dearmor -o /etc/apt/trusted.gpg.d/luigifab.gpg
echo "deb http://ppa.launchpad.net/luigifab/packages/ubuntu focal main" | sudo tee -a /etc/apt/sources.list
sudo apt update
sudo apt install awf-gtk2 awf-gtk3 awf-gtk4

# sha256sum /etc/apt/trusted.gpg.d/luigifab.gpg
578c89a677048e38007462d543686b53587efba9f93814601169253c45ff9213
# apt-key list
/etc/apt/trusted.gpg.d/luigifab.gpg
pub   rsa4096 2020-10-31 [SC]
      458B 0C46 D024 FD8C B8BC  99CD FFE5 BD43 9356 DF7D
```

## Blurry text with GTK 4

If font rendering is bad, add in `~/.config/gtk-4.0/settings.ini`:

```
[Settings]
gtk-font-rendering=manual
gtk-hint-font-metrics=1
gtk-xft-hintstyle=hintfull
gtk-xft-antialias=0
gtk-xft-hinting=1
```

## Dev

To reload theme when source files change, you can use [Entr](https://github.com/eradman/entr) with the `SIGHUP` signal:
```
sudo apt install entr  or  sudo dnf install entr  or  sudo zypper install entr  or  ...
ls ~/.themes/yourtheme/gtk-3*/*.css | entr killall -s SIGHUP awf-gtk3
```

## Copyright

- Current version: 2.8.1 (03/03/2025)
- Compatibility: GTK 2.24 / 3.0..3.24 / 4.0..4.17
- Links: [luigifab.fr](https://www.luigifab.fr/gtk/awf-extended) - [github.com](https://github.com/luigifab/awf-extended)\
[Arch Linux awf-gtk2.zst](https://aur.archlinux.org/packages/awf-gtk2)
; [Arch Linux awf-gtk3.zst](https://aur.archlinux.org/packages/awf-gtk3)
; [Arch Linux awf-gtk4.zst](https://aur.archlinux.org/packages/awf-gtk4)\
[Debian awf-gtk3.deb,  awf-gtk4.deb](https://packages.debian.org/awf-gtk)\
[Fedora awf-gtk2.rpm](https://src.fedoraproject.org/rpms/awf-gtk2)
; [Fedora awf-gtk3.rpm](https://src.fedoraproject.org/rpms/awf-gtk3)
; [Fedora awf-gtk4.rpm](https://src.fedoraproject.org/rpms/awf-gtk4)\
[openSUSE awf-gtk2.rpm](https://software.opensuse.org/package/awf-gtk2)
; [openSUSE awf-gtk3.rpm](https://software.opensuse.org/package/awf-gtk3)
; [openSUSE awf-gtk4.rpm](https://software.opensuse.org/package/awf-gtk4)\
[Mageia awf-gtk2.rpm](https://madb.mageia.org/package/show/name/awf-gtk2/arch/x86_64)
; [Mageia awf-gtk3.rpm](https://madb.mageia.org/package/show/name/awf-gtk3/arch/x86_64)
; [Mageia awf-gtk4.rpm](https://madb.mageia.org/package/show/name/awf-gtk4/arch/x86_64)\
[Trisquel awf-gtk3.deb, awf-gtk4.deb](https://packages.trisquel.org/awf-gtk)\
[Ubuntu awf-gtk3.deb, awf-gtk4.deb](https://packages.ubuntu.com/awf-gtk)\
[Ubuntu PPA](https://launchpad.net/~luigifab/+archive/ubuntu/packages)

This program is provided under the terms of the **GNU GPLv3+** license.\
If you like, take some of your time to improve the translations, go to https://bit.ly/2HyCCEc.

## Packages in official distros repositories

[![Packages status](https://repology.org/badge/vertical-allrepos/awf-widget-factory.svg?header=awf-gtk&minversion=2.0.0&columns=3)](https://repology.org/project/awf-widget-factory/versions)

## Credits

Forked from [awf](https://github.com/valr/awf) by Valère Monseur (valr).
