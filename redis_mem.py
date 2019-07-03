import redis
import time

r = redis.Redis(
    host='localhost',
    port=6379)

data='abdqwbeujqehujqkahwsdjkwqgherjqwabndjkgqukwjehnkqwbadxukjqwghjkkbjdklbqwuikbjklhgeujkdqwbnadsxjkbquwkgedujkqwbsdjkxhqwuikhbedjkgbqwujkasgxjkqwbeukdsgq'

iter = 100000

start_time = time.time()

for i in range(0, iter):
    r.set('foo', data)
    value = r.get('foo')

print(time.time() - start_time)
