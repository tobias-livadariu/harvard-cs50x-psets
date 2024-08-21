// Note ChatGPT helped me develop this function.
function digUpSkeletons() {
    fetch('/digUpSkeletons', {
        method: 'POST',
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('skeleton-count').textContent = data.skeletonCount;
        document.getElementById('total-skeletons').textContent = data.totalSkeletons;
    });
}
