# weibo download
import json
import sys
import time
# from ss import cd
from ss import get_chrome_driver

def pfe(c: str) -> None:
    '''
    Print & flush to stderr.
    '''
    print(c, end='', file=sys.stderr)
    sys.stdout.flush()


def fj(d) -> str:
    '''
    Format JSON.
    '''
    return json.dumps(d, indent=4, ensure_ascii=False)


def work(driver) -> None:
    pfe('.')
    driver.get('https://weibo.com/ajax/statuses/mymblog?uid=7198559139&page=1&feature=0')
    time.sleep(1)
    
    pfe('.')
    while 'Visitor' in driver.title:
        time.sleep(1)
        pfe(driver.title)
    
    jsondat = driver.page_source.rstrip('</pre></body></html>').lstrip('<html><head></head><body><pre style="word-wrap: break-word; white-space: pre-wrap;">')
    jsondat = json.loads(jsondat)
    print(fj(jsondat))


if __name__ == '__main__':
    pfe('.')
    driver = get_chrome_driver()
    
    if driver == None:
        pfe('Driver down?!')
        sys.exit(-1)
  
    try:
        work(driver)
    except Exception as e:
        print(e)


    driver.close()
    driver.quit()


