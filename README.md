stacklr_tui [![Build Status](https://travis-ci.org/mamewotoko/stacklr_tui.svg?branch=master)](https://travis-ci.org/mamewotoko/stacklr_tui)
==========

Text user interface of stacklr for desktop

Build
-----

```
make
```

Prepare
-------
create item text (e.g. data/Stock.txt)

Run (ubuntu)
-------------

```
./stacklr_tui
```
key bindings
up, down: move focus
F1, q:  exit.

Run (docker)
-------------

1. build docker container image

```
docker-compose build
```

2. build stackr_tui app

```
docker-compose run stacklr_tui make
```

3. run stackr_tui app

```
docker-compose run --entrypoint ./stacklr_tui  stacklr_tui
```

TODO
----
* add minimum function
  * add enter item ui
  * move focused item to next group when space key is pressed
    * refresh view
  * save item on exit
* change background color of group name
* support expand/collapse
* load items from google tasks & calendar
  * multithread?
* Test
  * CUnit: difficult to compile
  * other tool

Reference
---------
* stacklr
  * [Google play](https://play.google.com/store/apps/details?id=com.mamewo.stacklr)
  * [GitHub](https://github.com/mamewotoko/stacklr)

----
Takashi Masuyama < mamewotoko@gmail.com >
http://mamewo.ddo.jp/
