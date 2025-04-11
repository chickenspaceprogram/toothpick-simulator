import numpy
import matplotlib.pyplot as plt
import copy

batch_size = 1000000000

def stderr(ntrials: int):
    return ((2 / numpy.pi) * (1 - 2 / numpy.pi) / ntrials) ** 0.5

data = numpy.genfromtxt('data/1kdata/all_data.csv', delimiter=',')
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
plt.scatter(xvals, errvals_95percent)
plt.plot(xvals, 1.96 * stderr(xvals))
plt.show()
