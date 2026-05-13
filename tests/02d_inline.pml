inline barrier() {
    skip
}

inline min(a, b) {
    if
    :: a > b -> a = b
    :: else -> skip
    fi
}