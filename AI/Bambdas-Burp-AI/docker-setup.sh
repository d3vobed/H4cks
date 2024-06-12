# docker_setup.sh
#!/bin/bash

# Dockerfile to set up Ollama AI model
cat << 'EOF' > Dockerfile
FROM python:3.9-slim

# Install necessary packages
RUN pip install ollama

# Copy and set up the Ollama model
COPY ollama_model /app/ollama_model
WORKDIR /app/ollama_model

# Expose port for the Ollama model API
EXPOSE 8000

# Run the Ollama model server
CMD ["python", "ollama_model.py"]
EOF

# Build and run Docker container
docker build -t ollama_model .
docker run -d -p 8000:8000 ollama_model
