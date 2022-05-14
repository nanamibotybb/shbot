#!/usr/bin/env python3
# selenium service
import os
import time
import selenium.webdriver
from selenium.webdriver.chrome.options import Options

DAT = '.cache.webdriver'


def export_dat(url, session_id):
    with open(DAT, 'w') as f:
        f.write(f'{url}\n{session_id}\n')


# return (url, session_id)
def import_dat():
    with open(DAT) as f:
        return [i.strip() for i in f.readlines() if i.strip()]


def cd():
    '''外部接口'''
    try:
        url, session_id = import_dat()
        instance = selenium.webdriver.Remote(
            command_executor=url, desired_capabilities={})
    except Exception as e:
        print(e)
        return
    instance.close() # 会新开一个窗口
    instance.session_id = session_id
    return instance


def get_chrome_driver():
    opt = Options()
    opt.add_argument('--headless')
    opt.add_argument('--no-sandbox')
    opt.add_argument('--disable-dev-shm-usgae')
    
    return selenium.webdriver.Chrome(chrome_options=opt)

    
if __name__ == '__main__':
    instance = get_chrome_driver()
    
    try:
        export_dat(instance.command_executor._url, instance.session_id)
        
        print('Ready')
        while True:
            time.sleep(1000)
            
    except KeyboardInterrupt:
        print('Goodbye')
        os.remove(DAT)
        instance.quit()
