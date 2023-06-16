#!/bin/bash
# Debian: sudo apt install dpkg-dev devscripts build-essential dh-make dh-autoreconf intltool libgtk2.0-dev libgtk-3-dev libgtk-4-dev


cd "$(dirname "$0")"
version="2.7.0"


rm -rf builder/
mkdir builder

# copy to a tmp directory
if [ true ]; then
	cd builder
	wget https://github.com/luigifab/awf-extended/archive/v$version/awf-extended-$version.tar.gz
	tar xzf awf-extended-$version.tar.gz
	cd ..
else
	temp=awf-extended-$version
	mkdir /tmp/$temp
	cp -r ../* /tmp/$temp/
	rm -rf /tmp/$temp/*/builder/

	mv /tmp/$temp builder/
	cp /usr/share/common-licenses/GPL-3 builder/$temp/LICENSE

	cd builder/
	tar czf $temp.tar.gz $temp
	cd ..
fi


# create packages for Debian and Ubuntu
for serie in experimental; do

	if [ $serie = "experimental" ]; then
		# for Ubuntu
		cp -a builder/awf-extended-$version/ builder/awf-extended-$version+src/
		# Debian only
		cd builder/awf-extended-$version/
	else
		# Ubuntu only
		cp -a builder/awf-extended-$version+src/ builder/awf-extended-$version+$serie/
		cd builder/awf-extended-$version+$serie/
	fi

	dh_make -s -y -f ../awf-extended-$version.tar.gz -p awf-gtk

	rm -f debian/*ex debian/*EX debian/README* debian/*doc*
	mkdir debian/upstream
	cp debian-gtk/* debian/
	rm debian/deb.sh
	mv debian/metadata debian/upstream/metadata



	if [ $serie = "experimental" ]; then
		dpkg-buildpackage -us -uc
	else
		# debhelper: experimental:13 focal:12 bionic:9 xenial:9 trusty:9
		if [ $serie = "focal" ]; then
			sed -i 's/debhelper-compat (= 13)/debhelper-compat (= 12)/g' debian/control
		fi
		if [ $serie = "bionic" ]; then
			sed -i 's/dh $@/dh $@ --with autoreconf/g' debian/rules
			sed -i 's/debhelper-compat (= 13)/debhelper-compat (= 9), dh-autoreconf/g' debian/control
		fi
		if [ $serie = "xenial" ]; then
			sed -i 's/dh $@/dh $@ --with autoreconf/g' debian/rules
			sed -i 's/debhelper-compat (= 13)/debhelper (>= 9), dh-autoreconf/g' debian/control
			sed -i ':a;N;$!ba;s/Rules-Requires-Root: no\n//g' debian/control
			echo 9 > debian/compat
		fi
		if [ $serie = "trusty" ]; then
			sed -i 's/dh $@/dh $@ --with autotools_dev,autoreconf/g' debian/rules
			sed -i 's/override_dh_update_autotools_config/override_dh_autotools-dev_updateconfig/g' debian/rules
			sed -i 's/debhelper-compat (= 13)/debhelper (>= 9), autotools-dev, dh-autoreconf/g' debian/control
			sed -i ':a;N;$!ba;s/Rules-Requires-Root: no\n//g' debian/control
			echo 9 > debian/compat
		fi
		sed -i 's/experimental/'$serie'/g' debian/changelog
		sed -i 's/-1) /-1+'$serie') /' debian/changelog
		dpkg-buildpackage -us -uc -ui -d -S
	fi
	echo "=========================== debsign =="
	cd ..

	if [ $serie = "experimental" ]; then
		# Debian only
		debsign awf-gtk_$version-*.changes
		echo "=========================== lintian =="
		lintian -EviIL +pedantic awf-gtk*_$version-*.deb
	else
		# Ubuntu only
		debsign awf-gtk*_$version*+$serie*source.changes
	fi
	echo "==========================="
	cd ..
done

ls -dlth "$PWD/"builder/*.deb "$PWD/"builder/*.changes
echo "==========================="

# cleanup
rm -rf builder/*/