import json
import sys
import time

# dx ['data']['list'].
# d from dx.


def translate_datetime(d: str) -> str:
    # Fri Mar 25 20:24:52 +0800 2022 -> Chinese style
    try:
        d1 = time.strptime(d, '%a %b %d %H:%M:%S %z %Y')
        d = time.strftime('%H:%M %m/%d %A', d1)
    except ValueError:
        pass
    
    return d


# Print weibo.
# d: const
def pw(d) -> None:
    print(f"weibo-{d['user']['screen_name']}发布了新微博：")
    print()
    print(d['text_raw'])
    print(d['source'])
    print()
    print('https://m.weibo.com/u/7198559139')
    print(translate_datetime(d['created_at']))


# argmax { f(i) }
# f: function
# lst: list, const
def argmax(lst, f) -> int:
    di = 0
    
    for i in range(len(lst)):
        if f(i) > f(di):
            di = i

    return di


# dx: const
def newest_index(dx) -> None:
    return argmax(dx, lambda x: int(dx[x]['id']))


if __name__ == '__main__':
    dx = json.load(sys.stdin)['data']['list']
    pw(dx[newest_index(dx)])
