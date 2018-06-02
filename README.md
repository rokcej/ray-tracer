# Ray tracer
## Installing libraries
* Installing Make and GCC:
	```bash
	sudo apt-get install build-essential
	```
* Installing SDL:
	```bash
	sudo apt-get install libsdl2-dev
	```

## Compiling and running
Make sure to run the following commands in the main directory of the repository.  
* Compiling and linking the code:
	```bash
	make
	```
* Running the program:
	* "Real-time" rendering on the screen:
		```bash
		build/main
		```
	* Rendering a `render.bmp` file:
		```bash
		build/main bmp
		```
