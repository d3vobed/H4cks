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
    addresses.forEach(function(address) {
        var myHeaders = new Headers();
        myHeaders.append("Content-Type", "application/json");

        var raw = JSON.stringify({
            "method": "eth_getBalance",
            "params": [address.trim(), "latest"], // Send each address individually
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
                if (data.result) {
                    var balanceInEther = parseInt(data.result, 16) / 1e18;
                    var balanceFixed = balanceInEther.toFixed(2)
                    document.getElementById('result').innerText += `\nBalance for ${address.trim()}: ${balanceFixed} ETH`; // Append result for each address
                } else {
                    document.getElementById('result').innerText += `\nError fetching balance for ${address.trim()}`;
                }
            })
            .catch(error => {
                document.getElementById('result').innerText += `\nError fetching balance for ${address.trim()}`;
                console.log('error', error);
            });
    });
}
