#!/bin/bash

# your dam path to the Burp Suite project file
BURP_PROJECT_FILE="$1"

# Fabric Pattern for filtering CSP issues
cat << EOF > csp_pattern.yaml
name: csp_pattern
description: Filter CSP issues from Burp Suite project file
inputs:
  - type: file
    name: burp_project_file
steps:
  - name: parse_burp_project
    type: parse_burp_project
    parameters:
      file: "\${inputs.burp_project_file}"
  - name: filter_csp_issues
    type: filter
    parameters:
      rules:
        - type: header
          name: Content-Security-Policy
        - type: header
          name: X-Content-Security-Policy
        - type: header
          name: X-WebKit-CSP
outputs:
  - name: csp_issues
    from: filter_csp_issues.result
EOF

# Run Fabric with the CSP pattern
fabric --pattern csp_pattern.yaml --input burp_project_file="$BURP_PROJECT_FILE"

# Clean up
rm csp_pattern.yaml
