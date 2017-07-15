all:
	g++ -o as2 film.cpp main2.cpp camera.cpp cartesian.cpp color.cpp light.cpp material.cpp matrix.cpp primitive.cpp raytracer.cpp sampler.cpp scene.cpp shapes.cpp transformation.cpp parser.cpp -I . -lpthread -lX11 -std=c++11

clean: 
	$(RM) as2