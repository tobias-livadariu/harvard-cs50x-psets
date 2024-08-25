function buyTenAutodiggers() {
    fetch("numAutodiggersBuyable", {
        method: "POST",
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById("skeleton-count").textContent = formatNumberSuffix(data.skeletonCount);
        document.getElementById("total-skeletons").textContent = formatNumberSuffix(data.totalSkeletons);

        // Updating the key-value pairs in userSkeletons
        userSkeletons.skeletonCount = data.skeletonCount;
        userSkeletons.totalSkeletons = data.totalSkeletons;
    });
}
