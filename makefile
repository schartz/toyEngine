CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanTest: *.cpp *.hpp
	g++ $(CFLAGS) -o VulkanTest.out *.cpp $(LDFLAGS)

.PHONY: test clean

test: VulkanTest
	./VulkanTest.out

clean:
	rm -f VulkanTest.out

all: test clean