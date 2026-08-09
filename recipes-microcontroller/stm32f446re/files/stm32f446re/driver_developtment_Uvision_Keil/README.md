# About Uvision Keil.

  Keil uVision is a comprehensive software development environment, primarily used for developing embedded applications, especially for Arm-based microcontrollers. It's essentially an IDE (Integrated Development Environment) that includes tools for project management, code editing, compilation, debugging, and simulation.

## Intallation guide on Ubuntu LTS 24.04 ( I have only tried it in this version of Ubuntu linux)

	Since you are in a Linux machine , there is no support for Uvision Keil. Therefore, you will need to install " Wine ". Wine is a compatibility layer that enables running Windows applications on Unix-like operating systems, including Linux. It translates Windows API calls into equivalent Linux calls, allowing Windows software to be executed without a full Windows environment.

	In short , you can run apllication on Linux that are meant to be Windows compatible only.

	Read more about it in the official page --> https://www.winehq.org/

### Wine Intallation guide (Required if using a linux distribution):

	Can be obtained from here. It is very well explained --> https://gitlab.winehq.org/wine/wine/-/wikis/Debian-Ubuntu 

	If you dont want to read it. Here is a fast explanation of what to do on the terminal.

#### Preparation:

		- If your system is 64 bit, enable 32 bit architecture:

			1). sudo dpkg --add-architecture i386

		- Make a note of your distribution name:Look for the line with either UBUNTU_CODENAME or VERSION_CODENAME. If both are present, use the name after UBUNTU_CODENAME.

			2). cat /etc/os-release 
		
#### Add the reposity:

		- Download and add the repository key:

			3). sudo mkdir -pm755 /etc/apt/keyrings
					wget -O - https://dl.winehq.org/wine-builds/winehq.key | sudo gpg --dearmor -o /etc/apt/keyrings/winehq-archive.key -

		- Add the repository: If your distribution name is not on the list, older packages may be available on the download server. Add one repository.
		
		  4). 
					<pre><code>## Ubuntu-based ### Ubuntu 25.04 (Plucky) sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/ubuntu/dists/plucky/winehq-plucky.sources ### Ubuntu 24.10 (Oracular) sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/ubuntu/dists/oracular/winehq-oracular.sources ### Ubuntu 24.04 / Linux Mint 22 (Noble) sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/ubuntu/dists/noble/winehq-noble.sources ### Ubuntu 22.04 / Linux Mint 21.x (Jammy) sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/ubuntu/dists/jammy/winehq-jammy.sources ### Ubuntu 20.04 / Linux Mint 20.x (Focal) sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/ubuntu/dists/focal/winehq-focal.sources ## Debian-based ### Debian Testing (Trixie) sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/debian/dists/trixie/winehq-trixie.sources ### Debian 12 (Bookworm) sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/debian/dists/bookworm/winehq-bookworm.sources ### Debian 11 (Bullseye) sudo wget -NP /etc/apt/sources.list.d/ https://dl.winehq.org/wine-builds/debian/dists/bullseye/winehq-bullseye.sources </code></pre>

		- Update the package information:

			5). sudo apt update

#### Install Wine:

		- Install one of the following packages:

			6). Personally I always get the stable branch.

				<pre><code>## Stable Branch sudo apt install --install-recommends winehq-stable ## Development Branch sudo apt install --install-recommends winehq-devel ## Staging Branch sudo apt install --install-recommends winehq-staging </code></pre>

DONE!

### Openning Uvision Keil after installing wine.


# Questions.

	Question: Why am I not able to load the image into the flash ram after compiling my program using Keil?
  R: I am not sure, it seems like using wine does not allow you to have the ability of flashing it to the device, or the ability to recognize that you have the drivers for it. A simple workout is to use the ARM compiler. Obtain the .AXF file from the Objects folder and make it into a .bin file extension. 

	Use the following commands on your terminal:

		arm-none-eabi-objcopy -O binary <project_name>.axf <project_name>.bin   
		sudo st-flash write stm32f446re_project.bin 0x8000000      NOTE:(You will need to download the stlink tools. Get it from here --> https://github.com/stlink-org/stlink )

