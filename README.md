# libmemcached

**Update: the bug has been fixed by Canonical so this repo is no longer of any use.**

This is a fork of the
[`libmemcached` library on Launchpad](https://launchpad.net/libmemcached) which
seem to be no longer maintained. The original README is in
[README.old](https://github.com/memcachier/libmemcached/blob/master/README.old).

This repo mainly exists to fix a
[security bug](https://bugs.launchpad.net/libmemcached/+bug/1381160)
([second bug report](https://bugs.launchpad.net/ubuntu/+source/libmemcached/+bug/1573594))
in the authentication code. This bug causes the error

```
MemcachedError: error 40 from memcached_get: FAILED TO SEND AUTHENTICATION TO SERVER, no mechanism available -> libmemcached/sasl.cc:238
```

which has been reported [here](https://github.com/heroku/heroku-buildpack-python/issues/201)
and [here](https://github.com/mozilla/standup/issues/334).

## Branches

* The branch `dev_1.0` mirrors `lp:libmemcached/1.0`.
* The branch `dev_1.2` mirrors `lp:libmemcached`.
* The `master` branch is a fork of the `1.0.18` tag (last stable version) and
  contains the bug fix.

```
         1.0.19 (master)
        /
---1.0.18---dev_1
                 \
------------------dev_1.2
```

## Install from source

To install `libmemcached` run:

```bash
$ git clone https://github.com/memcachier/libmemcached.git
$ cd libmemcached
$ sudo apt-get install libtool automake flex bison python-sphinx libsasl2-dev
$ ./bootstrap.sh autoreconf
$ ./configure --enable-sasl
```

If you get

```bash
configure: error: cannot find install-sh, install.sh, or shtool in "." "./.." "./../.."
```

make sure to have the `shtool` in the `libmemcached` directory (don't ask me why):

```bash
$ sudo apt-get install shtool
$ ln -s /usr/bin/shtool shtool
```

and continue:

```bash
$ ./configure --enable-sasl
$ make
$ sudo make install
```

This will install the library in `/usr/local/lib`.

## Install `pylibmc`

To install `pylibmc` using the fixed `libmemcached` run

```bash
$ sudo apt-get install python3-dev libz-dev
$ pip install pylibmc --install-option="--with-libmemcached=/usr/local/lib"
```
