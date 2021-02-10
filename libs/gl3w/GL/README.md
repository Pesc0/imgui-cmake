**IMPORTANT**

The file `gl3w.c` has been modified to link against `libbrcmGLESv2.so` when the macro `__RASPBIAN__` is defined.
The exact modifications can be seen in the patch file found [here](https://github.com/ocornut/imgui/issues/2822#issuecomment-573319787).