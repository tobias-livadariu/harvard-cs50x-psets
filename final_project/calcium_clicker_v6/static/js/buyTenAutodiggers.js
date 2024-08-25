function buyTenAutodiggers() {
    fetch("numAutodiggersBuyable", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        /* Getting the max number of autodiggers the user can buy. */
        let numAutodiggersBuyable = data.numAutodiggersBuyable
        if (numAutodiggersBuyable < 10) {
            throw new Error("10x transaction failed")
        }

        /* Buying 10 autodiggers for the user sequentially.
        Note that ChatGPT helped me write the syntax to make the
        calls sequential, helping to avoid race conditions and
        other issues.*/
        let promises = [];
        for (let i = 0; i < 10; i++) {
            promises.push(buyAutodigger());
        }
        return Promise.all(promises);  // Ensures all buyAutodigger() calls are completed
    })
    .catch(error => {
        console.error("Error during purchase:", error);
    });
}
