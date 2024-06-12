from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/predict', methods=['POST'])
def predict():
    data = request.get_json()
    response = {"prediction": "sample response"}  
    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000)
