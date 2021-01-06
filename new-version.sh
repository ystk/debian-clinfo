#!/bin/sh

# Change the version recorded in src/clinfo.c and man/clinfo.1 to
# the current highest OpenCL supported standard followed by current
# yy.mm.dd

abort() {
	echo "$1" >&2
	exit 1
}

test -n "$(git status --porcelain | grep -v '??')" && abort "Uncommited changes, aborting"

DATE=$(date +%Y-%m-%d)
MAJOR=$(awk '/^OpenCL/ { print $NF ; quit }' man/clinfo.1)
SUBV=$(date +%y.%m.%d)
VERSION="$MAJOR$SUBV"


sed -i -e "/clinfo version/ s/version \S\+\"/version $VERSION\"/" src/clinfo.c
sed -i -e "1 s/\".\+$/\"$DATE\" \"clinfo $VERSION\"/" man/clinfo.1

git commit -m "Version $VERSION" -e -a && git tag $VERSION

