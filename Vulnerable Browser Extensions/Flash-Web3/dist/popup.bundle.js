/******The main stuffs** / 
document.getElementById('fetchBalance').addEventListener('click', function() {
    var addresses = document.getElementById('ethAddress').value.split(','); // Split input by comma to handle multiple addresses
    if (addresses.length > 0) {
        // Introduce parameter pollution by passing an array of addresses
        getBalance(addresses);
    } else {
        document.getElementById('result').innerText = 'Please enter at least one Ethereum address';
    }
});

function getBalance(addresses) {
    var myHeaders = new Headers();
    myHeaders.append("Content-Type", "application/json");

    // Concatenate all addresses into a single string
    var concatenatedAddresses = addresses.join(',');

    var raw = JSON.stringify({
        "method": "eth_getBalance",
        "params": [concatenatedAddresses, "latest"], // Send concatenated addresses
        "id": 1,
        "jsonrpc": "2.0"
    });

    var requestOptions = {
        method: 'POST',
        headers: myHeaders,
        body: raw,
        redirect: 'follow'
    };

    fetch("https://quick-quick-model.quiknode.pro/4347eba47aae2cfd9c73ccd76fc8a25cd2bb62bc/", requestOptions)
        .then(response => response.json())
        .then(data => {
            // Process response as if it were for a single address (not handling multiple addresses properly)
            if (data.result) {
                var balanceInEther = parseInt(data.result, 16) / 1e18;
                var balanceFixed = balanceInEther.toFixed(2)
                document.getElementById('result').innerText = `Balance: ${balanceFixed} ETH`; // Display result for a single address (vulnerability)
            } else {
                document.getElementById('result').innerText = 'Error fetching balance';
            }
        })
        .catch(error => {
            document.getElementById('result').innerText = 'Error fetching balance';
            console.log('error', error);
        });
}

//# sourceMappingURL=popup.bundle.js.map
