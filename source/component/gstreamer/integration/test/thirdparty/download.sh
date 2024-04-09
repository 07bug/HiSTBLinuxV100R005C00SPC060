#!/bin/bash

function download()
{
    FILE=$1;
    FILE_DOWNLOAD=$2;
    URL=$3;
    if [ -f $FILE ]; then
        echo $FILE "already exists."
    else
        echo "download" $FILE_DOWNLOAD "from " $URL;
        wget --no-check-certificate $URL;
        echo "download" $FILE_DOWNLOAD "ok";
    fi
}

FILE=gst-libav-1.10.4.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://gstreamer.freedesktop.org/src/gst-libav/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL
echo haha;
exit;
echo lala;

FILE=gettext-0.19.8.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://ftp.gnu.org/pub/gnu/gettext/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=glib-2.46.2.tar
FILE_DOWNLOAD=$FILE.xz
URL=http://ftp.acc.umu.se/pub/gnome/sources/glib/2.46/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL
xz -d $FILE_DOWNLOAD

FILE=gmp-6.1.2.tar.bz2
FILE_DOWNLOAD=$FILE
URL=https://gmplib.org/download/gmp/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=gst-libav-1.10.4.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://gstreamer.freedesktop.org/src/gst-libav/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=gst-omx-1.10.4.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://gstreamer.freedesktop.org/src/gst-omx/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=gst-plugins-bad-1.10.4.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://gstreamer.freedesktop.org/src/gst-plugins-bad/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=gst-plugins-base-1.10.4.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://gstreamer.freedesktop.org/src/gst-plugins-base/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=gst-plugins-good-1.10.4.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://gstreamer.freedesktop.org/src/gst-plugins-good/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=gst-validate-1.10.4.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://gstreamer.freedesktop.org/src/gst-validate/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=gstreamer-1.10.4.tar.xz
FILE_DOWNLOAD=$FILE
URL=https://gstreamer.freedesktop.org/src/gstreamer/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=libffi-3.2.1.tar.gz
FILE_DOWNLOAD=$FILE
URL=ftp://sourceware.org/pub/libffi/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=libiconv-1.14.tar.gz
FILE_DOWNLOAD=$FILE
URL=https://ftp.gnu.org/pub/gnu/libiconv/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=libsoup-2.58.0.tar.xz
FILE_DOWNLOAD=$FILE
URL=http://ftp.gnome.org/pub/GNOME/sources/libsoup/2.48/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=libxml2-2.9.4.tar.gz
FILE_DOWNLOAD=$FILE
URL=ftp://xmlsoft.org/libxml2/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=nettle-3.3.tar.gz
FILE_DOWNLOAD=$FILE
URL=https://ftp.gnu.org/gnu/nettle/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL

FILE=sqlite-autoconf-3180000.tar.gz
FILE_DOWNLOAD=$FILE
URL=http://ftp.osuosl.org/pub/blfs/conglomeration/sqlite/$FILE_DOWNLOAD
download $FILE $FILE_DOWNLOAD $URL
