import numpy
import matplotlib.pyplot as plt
import scipy
import copy

batch_size = 10000000

def stderr(ntrials: int):
    return ((2 / numpy.pi) * (1 - 2 / numpy.pi) / ntrials) ** 0.5

data = numpy.genfromtxt('data/bigdata/bigdata.csv', delimiter=',')
result = []
for elem in data:
    sum_val = 0
    temp = []
    for (index, value) in enumerate(elem):
        sum_val += value
        temp.append(sum_val / (index + 1))
    result.append(temp)

result2 = numpy.array(result).transpose()

means = copy.deepcopy([sum(i) / len(i) for i in result2])
errs = [[abs(val - means[i]) for val in lst]for (i, lst) in enumerate(result2)]
for i in errs:
    i.sort()

errvals_95percent = [i[int(0.95 * len(i))] for i in errs]
xvals = numpy.arange(batch_size, batch_size * (len(errvals_95percent) + 1), batch_size)
fig = plt.figure()
ax = fig.add_subplot()
ax.loglog()
ax.set_xlabel('Number of trials, $n$', fontsize=18)
ax.set_ylabel('95th percentile deviation from the mean, $E$', fontsize = 18)
ax.tick_params(labelsize=18)
plt.scatter(xvals, errvals_95percent)

polydata = numpy.polyfit(numpy.log10(xvals), numpy.log10(errvals_95percent), 1)
polyfn = numpy.poly1d(polydata)
plt.plot(xvals, 10 ** polyfn(numpy.log10(xvals)))
ax.text(10 ** 9.5, 10 ** -4, r"$\log_{10}(E) = " + f"{round(polydata[1], 4)} {round(polydata[0], 4)}" + r"\cdot\log_{10}(n)$", fontsize=20)
scipy_linregress = scipy.stats.linregress(numpy.log10(xvals), numpy.log10(errvals_95percent))
ax.text(10 ** 9.5, 10 ** -4.3, r"$R^2 = " + f"{round(scipy_linregress.rvalue ** 2, 4)}$", fontsize=20)
print(polydata)
print(scipy_linregress)

#plt.plot(xvals, 1.96 * stderr(xvals))
plt.show()
