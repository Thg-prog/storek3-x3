fn main() {
    let f = |x: f64| x.powi(3) + 4.0 * x - 3.0;

    let mut a = -10.0; // Левая граница интервала
    let mut b = 10.0; // Правая граница интервала
    let epsilon = 1e-6; // Заданная точность

    let root_bisection = find_root_bisection(&f, a, b, epsilon);
    println!("Приближенный корень с использованием половинного деления: {}", root_bisection);

    let root_newton = find_root_newton(&f, 0.0, epsilon);
    println!("Приближенный корень с использованием метода Ньютона: {}", root_newton);
}

fn find_root_bisection(f: &dyn Fn(f64) -> f64, mut a: f64, mut b: f64, epsilon: f64) -> f64 {
    while b - a > epsilon {
        let midpoint = (a + b) / 2.0;
        if f(midpoint) == 0.0 {
            // Найден корень
            return midpoint;
        } else if f(a) * f(midpoint) < 0.0 {
            b = midpoint;
        } else {
            a = midpoint;
        }
    }

    (a + b) / 2.0
}

fn find_root_newton(f: &dyn Fn(f64) -> f64, mut x0: f64, epsilon: f64) -> f64 {
    let mut x = x0;
    while f(x).abs() > epsilon {
        let derivative = (f(x + epsilon) - f(x)) / epsilon;
        x = x - f(x) / derivative;
    }
    x
}
