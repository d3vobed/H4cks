from flask import Flask, request, jsonify, re, openai
from burp import IBurpExtender, IProxyListener, IHttpRequestResponse, IHttpService
from java.util import ArrayList, HashMap, HashSet
from functools import wraps


app = Flask(__name__)

@app.route('/predict', methods=['POST'])
def predict():
    data = request.get_json()
    response = {"prediction": "sample response"}  
    return jsonify(response)

@app.errorhandler(404)
def not_found(e):
    return jsonify({"error": "The requested resource was not found."}), 404

@app.errorhandler(500)
def server_error(e):
    return jsonify({"error": "An internal server error occurred."}), 500        

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000)
