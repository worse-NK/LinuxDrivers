# Название объекта модуля, который нужно собрать
obj-m += hello_world.o

# Основные команды сборки и очистки
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean