fn main() {
    let f = |x: f64| 2.0 * x / (x * x + 1.0);

    let mut a = -10.0; // Левая граница интервала
    let mut b = 10.0; // Правая граница интервала
    let epsilon = 1e-6; // Заданная точность

    while b - a > epsilon {
        let midpoint = (a + b) / 2.0;
        if f(midpoint) == 0.0 {
            // Найден корень
            println!("Корень: {}", midpoint);
            break;
        } else if f(a) * f(midpoint) < 0.0 {
            b = midpoint;
        } else {
            a = midpoint;
        }
    }

    let root = (a + b) / 2.0;
    println!("Приближенный корень: {}", root);
}
