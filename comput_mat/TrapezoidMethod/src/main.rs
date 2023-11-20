fn trapezoidal_rule(a: f64, b: f64, n: usize) -> f64 {
    let h = (b - a) / n as f64; // Ширина каждой трапеции
    let mut integral = 0.0;

    for i in 1..n {
        let x_i = a + i as f64 * h;
        integral += 1.0 / x_i.ln();
    }

    // Добавляем значения на границах интервала
    integral += 0.5 * (1.0 / a.ln() + 1.0 / b.ln());

    integral *= h;

    integral
}

fn simpson_rule(a: f64, b: f64, n: usize) -> f64 {
    let h = (b - a) / n as f64;
    let mut integral = 1.0 / a.ln() + 1.0 / b.ln(); // Значения на границах интервала

    for i in 1..n {
        let x_i = a + i as f64 * h;
        if i % 2 == 0 {
            integral += 2.0 / x_i.ln();
        } else {
            integral += 4.0 / x_i.ln();
        }
    }

    integral *= h / 3.0;

    integral
}

fn main() {
    let a = 2.0; // Нижний предел интегрирования
    let b = 5.0; // Верхний предел интегрирования
    let n = 1000; // Количество трапеций

    let mut  result = trapezoidal_rule(a, b, n);
    println!("Результат интегрирования: {}", result);

    result = simpson_rule(a, b, n);
    println!("Результат интегрирования(simpson): {}", result);
}
