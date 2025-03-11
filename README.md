


# HOW THIS SHIT WORKS: 

## commands to flash: 
```
sudo qmk flash -c -kb etraxis/encorne -km testFork -bl avrdude-split-left # for left side
sudo qmk flash -c -kb etraxis/encorne -km testFork -bl avrdude-split-right # for right side
```

## how to flash:
just use command to flash => wait for compilation finish (SUDO IS ESSENTIAL!) => connect keyboar with reset pin connected to ground => disconnect pins from each other

## How to make small keymap changes and flash them with QMK through Nix
Actual nix guide taken from [here](https://www.bclaud.com.br/posts/qmk-flash-cantor/)

I have a Cantor split keyboard, which I bought assembled and just flashed with the help of a friend (thanks Felipe :D).

Unfortunately, I couldn’t get used with the stock miryoku homerow tapping Term (like a delay), and I wanted to decrease it. 

Since I’m using Linux, the approach I chose was to use Nix to “install” qmk. It’s not documented, but I’m familiar enough with it to try. Turns out it worked very well. If you want to follow my steps, install it too. https://nixos.org/download.html#download-nix

Clone qmk-firmware Repo and make sure your preferred keymap is update in main branch, otherwise follow your specific keymap guide to merge any difference. Miryoku guide for reference https://github.com/manna-harbour/miryoku_qmk/tree/miryoku/users/manna-harbour_miryoku#merge

My keymap is the default 5x3-3 and at the time it was updated. So I didn’t have to worry about merging diffs.

To decrease the term I’ve mentioned, I just had to change config.h file under manna-harbour users folder. Not going into details here because I’m sure there are better ways of doing it.

```[nix-shell:~/Side/qmk_firmware/users/manna-harbour_miryoku]$ ls
config.h  custom_config.h  custom_rules.mk  manna-harbour_miryoku.c  manna-harbour_miryoku.h  miryoku_babel  post_rules.mk  readme.org  rules.mk
```
Ok, to finish the setup, go to qmk-firmware root folder and type. 
```
nix-shell
```
It will take about ten minutes to run. After that, ‘qmk’ will be fully available in your current shell through nix. Before flashing, type
```
qmk doctor
```
And any problems will be displayed to you with a probable solution. Follow those instructions.

With all set, plug your keyboard microcontroller in bootloader mode, in my case was just holding top-left/right key before connecting to USB. Now if you type lsusb (with another keyboard, lol)

If you see a device a device in “DFU mode” in the list you’re good to go.

Perfect, now flash your firmware with a command similar to that one:
```
qmk flash -c -kb cantor -km manna-harbour_miryoku
```

Do the same thing for the other side and done! Now you can close your current shell and QMK installation software will no longer be in your path. To do that again, just go back to qmk-firmware folder and nix-shell. That time it won’t take long.

This isn’t intended to be a guide, I’m just backing up the steps I took.

The documentation from either QMK, Cantor and Maryoku are very good but very extensive at the same time, but I don’t want to read them again to make such a tiny change haha.

Hope it helps someone else too :). see ya
