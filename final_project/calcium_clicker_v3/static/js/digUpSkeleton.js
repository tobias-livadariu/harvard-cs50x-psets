// Note ChatGPT helped me develop this function.
function digUpSkeleton() {
    fetch('/resurrect', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        }
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('skeleton-count').textContent = data.skeletonCount;
    });
}
