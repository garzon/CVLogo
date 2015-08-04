#!-*-coding: utf-8 -*-
from selenium import webdriver
import urllib
import re


class Url:
    
    def __init__(self, _template_url):
        self._template_url = _template_url

    def set_param(self, *args):
        args = tuple([urllib.quote_plus(url) for url in args])
        self._url = self._template_url % args
        
    def get_url(self):
        return self._url


class Request:

    def __init__(self, Url, *args, **kwargs):
        self._Url = Url
        self._lock = False
        self.driver = webdriver.Firefox()

    def run(self):
        url = self._Url.get_url()
        if self._lock is False:
            self._lock = True
            self.driver.get(url)
        else:
            raise Exception("Driver is occupied")

    def finish(self):
        self.driver.close()
        self._lock = False

    def xpath(self, query_str):
        if self._lock is True:
            return self.driver.find_element_by_xpath(query_str)
        else:
            raise Exception("Object did not occupy driver")

    def css(self, query_str):
        if self._lock is True:
            return self.driver.find_elements_by_css_selector(query_str)
        else:
            raise Exception("Object did not occupy driver")
    


for i in range(10)[1:]:
    url = Url("https://s.taobao.com/search?q=%s&s=%s")
    url.set_param("阿迪达斯", str(i*44))

    req = Request(url)
    req.run()

    opener = urllib.URLopener()

    for a in req.css(".J_U2IStat"):
        url = Url(a.get_attribute("href"))
        url.set_param()
        req = Request(url)
        req.run()
        for a in req.css("#J_UlThumb li a img"):
            url = a.get_attribute("src")
            url = re.sub("60x60q90", "430x430q90", url)
            url = re.sub("50x50", "400x400", url)
            print url
            opener.retrieve(url, url[url.rfind("/")+1:])
        req.finish()
    req.finish()
