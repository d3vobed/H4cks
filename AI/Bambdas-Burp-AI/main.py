import requests
import json
import openai
from dotenv import load_dotenv
from importlib import resources
from functools import wraps
from flask import Flask, request, jsonify
from functools import wraps
import re
import requests
import os
from dotenv import load_dotenv
from importlib import resources
from burp import IBurpExtender, IProxyListener, IHttpRequestResponse, IHttpService
from java.util import ArrayList, HashMap, HashSet

# Connection to Ollama model hosted on Docker
OLLAMA_URL = "http://localhost:8000/predict"

def get_prediction(data):
    response = requests.post(OLLAMA_URL, json=data)
    return response.json()

# Fabric Fraction tool implementation
def fabric_fraction(data):
    # Implement Fabric Fraction efficiency enhancements
    return data  # Placeholder

class VulnParamGroup:
    def __init__(self, title, color, *parameterNames):
        self.title = title
        self.color = color
        self.parameterNames = parameterNames

open-redirect = VulnParamGroup("OPEN-REDIRECT", "BLUE", "redirect", "dom", "url", "nonce", "iframe.src", "location.href, "sink", "authDisplayType", "inline", "onload", "src_doc" )
ssrf = VulnParamGroup("SSRF", "GREEN", "dest", "redirect", "uri", "path", "continue", "url", "window", "next", "data", "reference", "site", "html", "val", "validate", "domain", "callback", "return", "page", "feed", "host", "port", "to", "out", "view", "dir")
sql = VulnParamGroup("SQL", "BLUE", "id", "page", "report", "dir", "search", "category", "file", "class", "url", "news", "item", "menu", "lang", "name", "ref", "title", "view", "topic", "thread", "type", "date", "form", "main", "nav", "region")
xss = VulnParamGroup("XSS", "ORANGE", "q", "s", "search", "id", "lang", "keyword", "query", "page", "keywords", "year", "view", "email", "type", "name", "p", "month", "image", "list_type", "url", "terms", "categoryid", "key", "l", "begindate", "enddate")
lfi = VulnParamGroup("LFI", "YELLOW", "cat", "dir", "action", "board", "date", "detail", "file", "download", "path", "folder", "prefix", "include", "page", "inc", "locate", "show", "doc", "site", "type", "view", "content", "document", "layout", "mod", "conf")
oPerson/vehicle detector guide  |  Vertex AI Vision  |  Google Cloudr_ = VulnParamGroup("OR", "PINK", "next", "url", "target", "rurl", "dest", "destination", "redir", "redirect_uri", "redirect_url", "redirect", "out", "view", "to", "image_url", "go", "return", "returnTo", "return_to", "checkout_url", "continue", "return_path")
rce = VulnParamGroup("RCE", "RED", "cmd", "exec", "command", "execute", "ping", "query", "jump", "code", "reg", "do", "func", "arg", "option", "load", "process", "step", "read", "feature", "exe", "module", "payload", "run", "print")

# Toggle for highlighting
highlightEnabled = True

# Set multi-vulnerable parameter group color
multipleVulnColor = "MAGENTA"
groups = [ssrf, open-redirect, sql, xss, lfi, or_, rce]
foundParams = HashSet()
colorCounts = HashMap()
combinedNotes = ""

class BurpExtender(IBurpExtender, IProxyListener):

    def registerExtenderCallbacks(self, callbacks):
        self._callbacks = callbacks
        self._helpers = callbacks.getHelpers()
        callbacks.setExtensionName("HTTP Smuggling Detector")
        callbacks.registerProxyListener(self)

    def processProxyMessage(self, messageIsRequest, message):
        if not messageIsRequest:
            requestResponse = message.getMessageInfo()
            request = requestResponse.getRequest()
            httpService = requestResponse.getHttpService()
            requestInfo = self._helpers.analyzeRequest(httpService, request)

            for group in groups:
                for paramName in group.parameterNames:
                    if self.hasParameter(requestInfo, paramName):
                        if highlightEnabled:
                            foundParams.add(f"{group.title}: {paramName}")
                            colorCounts.put(group.color, colorCounts.getOrDefault(group.color, 0) + 1)

                        if not highlightEnabled:
                            self.setHighlight(requestResponse, group.color)
                            return True

            if not foundParams.isEmpty():
                highlightColor = multipleVulnColor
                if colorCounts.size() == 1:
                    highlightColor = list(colorCounts.keySet())[0]

                self.setHighlight(requestResponse, highlightColor)
                combinedNotes = ", ".join(foundParams)
                self.setNotes(requestResponse, combinedNotes)
                return True

    def hasParameter(self, requestInfo, paramName):
        parameters = requestInfo.getParameters()
        for param in parameters:
            if param.getName() == paramName:
                return True
        return False

    def setHighlight(self, requestResponse, color):
        requestResponse.getAnnotations().setHighlightColor(color)

    def setNotes(self, requestResponse, notes):
        requestResponse.getAnnotations().setNotes(notes)


if __name__ == '__main__':
    sample_http_requests = [
        # List of sample HTTP requests
    ]
    vulnerabilities = analyze_http_requests(sample_http_requests)
    print("Vulnerabilities found:", vulnerabilities)
