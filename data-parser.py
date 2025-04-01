import numpy

data = numpy.genfromtxt('out.csv', delimiter=',')
sorted_data = numpy.sort(data)
print(f"min={}\nmax={}"
