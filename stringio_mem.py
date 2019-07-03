import io
import time

output = io.StringIO()
'''
output.write('First line')
#print('Second line.', file=output)

# Retrieve file contents -- this will be
# 'First line.\nSecond line.\n'
contents = output.getvalue()

print(contents)
'''
# Close object and discard memory buffer --
# .getvalue() will now raise an exception.

data='abdqwbeujqehujqkahwsdjkwqgherjqwabndjkgqukwjehnkqwbadxukjqwghjkkbjdklbqwuikbjklhgeujkdqwbnadsxjkbquwkgedujkqwbsdjkxhqwuikhbedjkgbqwujkasgxjkqwbeukdsgq'

iter = 100000

start_time = time.time()

for i in range(0, iter):
    output.write(data)
    value = output.getvalue()

print(time.time() - start_time)

output.close()
