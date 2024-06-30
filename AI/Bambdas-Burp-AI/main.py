import requests
import json
import os
from dotenv import load_dotenv
from burp import IBurpExtender, IProxyListener, IHttpRequestResponse, IHttpService
from java.util import HashMap, HashSet

# Load environment variables
load_dotenv()

# Constants
OLLAMA_URL = "http://localhost:8000/predict"
FABRIC_URL = "http://localhost:8000/fabric"

# Get prediction from Open-Interpreter
def get_prediction(data):
    response = requests.post(OLLAMA_URL, json=data)
    return response.json()

# Fabric Fraction tool implementation
def fabric_fraction(data):
    response = requests.post(FABRIC_URL, json={"data": data})
    return response.json()

class VulnParamGroup:
    def __init__(self, title, color, *parameterNames):
        self.title = title
        self.color = color
        self.parameterNames = parameterNames

xss = VulnParamGroup("XSS", "ORANGE", "q", "s", "search", "id", "lang", "keyword", "query", "page", "keywords", "year", "view", "email", "type", "name", "p", "month", "image", "list_type", "url", "terms", "categoryid", "key", "l", "begindate", "enddate")

highlightEnabled = True
multipleVulnColor = "MAGENTA"
groups = [xss]
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
