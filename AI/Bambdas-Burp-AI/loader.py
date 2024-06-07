import os
import requests
import subprocess
import time

# Function to interact with Ollama AI instance
def communicate_with_ollama(message):
    # Assuming the Ollama AI instance is running on Docker with port 8000 exposed
    url = "http://localhost:8000/ollama"
    payload = {"message": message}
    response = requests.post(url, json=payload)
    return response.json()

# Function to check if everything is okay using Tib3rius' Tib Tubs
def check_with_tib_tubs():
    # Assuming Tib Tubs is integrated with PortSwigger's BApp Store API
    bapp_store_api_url = "https://portswigger.net/api"
    bapp_id = "tib-tubs"
    url = f"{bapp_store_api_url}/bapp/{bapp_id}/status"
    response = requests.get(url)
    return response.json()

# Function to speak the output using Tib3rius' Tib Tubs
def speak_output(output):
    # Assuming Tib Tubs is integrated with PortSwigger's BApp Store API
    bapp_store_api_url = "https://portswigger.net/api"
    bapp_id = "tib-tubs"
    url = f"{bapp_store_api_url}/bapp/{bapp_id}/speak"
    payload = {"message": output}
    requests.post(url, json=payload)

# Main function
def main():
    # Initialization
    initialization_message = "Initializing..."
    initialization_response = communicate_with_ollama(initialization_message)
    print(initialization_response)

    # Check if everything is okay
    check_result = check_with_tib_tubs()
    if check_result["status"] == "ok":
        output_message = "Everything is okay."
        print(output_message)
        # Speak the output
        speak_output(output_message)
    else:
        print("Something went wrong!")

if __name__ == "__main__":
    main()
