

Las bibliotecas en su versi�n para los sistemas operativos tipo Linux no se han incluido debido a que son paquetes com�nmente incluidos en la mayor�a de distribuciones y es m�s sencillo instalarlas mediante el gestor de paquetes de la distribuci�n que se utilice.

En el caso de la distribuci�n Ubuntu (puesto que Ubuntu es de la familia de Debian, la disponibilidad de paquetes ser� similar en toda la familia) se ha incluido un peque�o tutorial con las �rdenes para lograr que el gestor de paquetes instale las bibliotecas de forma autom�tica.

Puesto que las instalaciones de OpenGL y GLEW son m�s dependientes de la tarjeta gr�fica disponible y del driver elegido, se excluyen del tutorial.

Los comandos que se deber�n ejecutar en la consola son los siguientes:


sudo apt-get update

sudo apt-get install build-essential checkinstall cmake pkg-config yasm

sudo apt-get install build-essential libgtk2.0-dev libjpeg-dev libtiff4-dev libjasper-dev libopenexr-dev cmake python-dev python-numpy python-tk libtbb-dev libeigen2-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev libqt4-dev libqt4-opengl-dev sphinx-common texlive-latex-extra libv4l-dev libdc1394-22-dev libavcodec-dev libavformat-dev libswscale-dev

sudo apt-get install libopencv-dev

sudo apt-get install libqt4-core libqt4-dev libqt4-gui qt4-dev-tools

sudo apt-get install libglm-dev

sudo apt-get install exiv2

sudo apt-get install libcgal-dev