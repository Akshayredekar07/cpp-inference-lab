// ════════════════════════════════════════════════════════════
// Pillar 2 — Abstraction: basic → medium → advanced
//
// Covers, in order:
//   1.  hidden storage                  (basic)
//   2.  abstract interface + concretes   (basic)
//   3.  utility class with statics      (basic)
//   4.  interface segregation           (medium)
//   5.  factory hides concrete type     (medium)
//   6.  template method via abstraction (medium)
//   7.  std::function as abstraction    (advanced)
//   8.  std::variant + std::visit       (advanced)
//   9.  CRTP — compile-time abstraction (advanced)
//
// Each numbered banner prints before the corresponding demo in main().
// Companion notes live in: 06-oop-basics/02-abstraction.md
// ════════════════════════════════════════════════════════════


#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

// Some toolchains (notably MinGW) do not expose M_PI by default.
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// ──── 1. hidden storage ────
// Caller sees add() / value() / count(). Container type and helper are
// private — both can change without breaking any caller.
class Average {
private:
    std::vector<double> samples;
    double total() const {
        return std::accumulate(samples.begin(), samples.end(), 0.0);
    }

public:
    void    add(double x) { samples.push_back(x); }
    double  value() const { return samples.empty() ? 0.0 : total() / samples.size(); }
    size_t  count() const { return samples.size(); }
};

void runHiddenStorage() {
    std::cout << "──── 1. hidden storage ────\n";

    Average a;
    a.add(10.0); a.add(20.0); a.add(30.0);
    std::cout << "  count = " << a.count() << ", value = " << a.value() << "\n";
}


// ──── 2. abstract interface + concretes ────
// Shape is abstract — caller code talks to Shape& / Shape* and never
// needs to know which concrete shape it has been given.
class Shape {
public:
    virtual double area()      const = 0;
    virtual double perimeter() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;
public:
    explicit Circle(double r) : radius(r) {}
    double area()      const override { return M_PI * radius * radius; }
    double perimeter() const override { return 2 * M_PI * radius; }
};

class Rectangle : public Shape {
private:
    double w, h;
public:
    Rectangle(double width, double height) : w(width), h(height) {}
    double area()      const override { return w * h; }
    double perimeter() const override { return 2 * (w + h); }
};

void runAbstractInterface() {
    std::cout << "──── 2. abstract interface ────\n";

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(2.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));

    for (const auto& s : shapes) {
        std::cout << "  area=" << s->area()
                  << "  perimeter=" << s->perimeter() << "\n";
    }
}


// ──── 3. utility class with statics ────
// A class with only static members works as a namespace with a nicer
// name — the formula is hidden behind intention-revealing calls.
class Temperature {
public:
    static double celsiusToFahrenheit(double c) { return c * 9.0 / 5.0 + 32.0; }
    static double fahrenheitToCelsius(double f) { return (f - 32.0) * 5.0 / 9.0; }
};

void runUtilityClass() {
    std::cout << "──── 3. utility class ────\n";

    std::cout << "  100C -> " << Temperature::celsiusToFahrenheit(100.0) << "F\n";
    std::cout << "   32F -> " << Temperature::fahrenheitToCelsius(32.0)   << "C\n";
}


// ──── 4. interface segregation ────
// Split a fat interface into small, role-based ones. A widget only
// implements the roles it actually supports.
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;
};

class Resizable {
public:
    virtual ~Resizable() = default;
    virtual void resize(double factor) = 0;
};

class Movable {
public:
    virtual ~Movable() = default;
    virtual void move(int dx, int dy)   = 0;
};

// A window can be all three.
class Window : public Drawable, public Resizable, public Movable {
private:
    double w = 1.0, h = 1.0;
    int    x = 0,  y = 0;
    std::string title = "untitled";

public:
    explicit Window(std::string t) : title(std::move(t)) {}

    void draw()   const override { std::cout << "  draw " << title
                                              << " (" << w << "x" << h << ")\n"; }
    void resize(double factor) override {
        w *= factor; h *= factor;
        std::cout << "  " << title << " -> " << w << "x" << h << "\n";
    }
    void move(int dx, int dy) override {
        x += dx; y += dy;
        std::cout << "  " << title << " moved to (" << x << "," << y << ")\n";
    }
};

void runInterfaceSegregation() {
    std::cout << "──── 4. interface segregation ────\n";

    Window win("editor");
    win.draw();
    win.resize(1.5);
    win.move(10, 20);
}


// ──── 5. factory hides concrete type ────
// Caller asks for a Shape by name; the factory picks the concrete type.
// The header only mentions the abstract return type.
enum class ShapeKind { Circle, Rectangle };

std::unique_ptr<Shape> makeShape(ShapeKind kind) {
    switch (kind) {
        case ShapeKind::Circle:    return std::make_unique<Circle>(1.0);
        case ShapeKind::Rectangle: return std::make_unique<Rectangle>(2.0, 3.0);
    }
    return nullptr;
}

void runFactory() {
    std::cout << "──── 5. factory hides concrete type ────\n";

    auto s = makeShape(ShapeKind::Circle);    // caller does not know / need to know
    std::cout << "  area = " << s->area() << "\n";
}


// ──── 6. template method via abstraction ────
// The base defines the skeleton of an algorithm; subclasses fill in
// the steps. The skeleton cannot be changed by subclasses.
class DataProcessor {
public:
    void run() {                          // template method — non-virtual
        read();
        transform();
        write();
    }

    virtual ~DataProcessor() = default;

protected:
    virtual void read()      { std::cout << "  read default data\n"; }
    virtual void transform() { std::cout << "  identity transform\n"; }
    virtual void write()     { std::cout << "  write default sink\n"; }
};

class UpperProcessor : public DataProcessor {
protected:
    void transform() override {
        std::cout << "  uppercase transform\n";
    }
};

void runTemplateMethod() {
    std::cout << "──── 6. template method ────\n";

    UpperProcessor u;
    u.run();                              // read + upper.transform + write
}


// ──── 7. std::function as abstraction ────
// Type erasure — the public type does not mention any concrete class.
// Adding a new behaviour means writing a lambda, not a new class.
class Button {
public:
    using Handler = std::function<void()>;

    void onClick(Handler h) { handlers.push_back(std::move(h)); }
    void click() {
        for (auto& h : handlers) h();
    }

private:
    std::vector<Handler> handlers;
};

void runStdFunction() {
    std::cout << "──── 7. std::function abstraction ────\n";

    Button b;
    b.onClick([] { std::cout << "  handler A fired\n"; });
    b.onClick([] { std::cout << "  handler B fired\n"; });

    int counter = 0;
    b.onClick([&counter] { ++counter; std::cout << "  counter=" << counter << "\n"; });

    b.click();
    b.click();                            // counter increments again
}


// ──── 8. std::variant + std::visit ────
// A closed set of alternative behaviours without inheritance. Visitor
// pattern in the standard library — one function per alternative.
struct CircleAlt    { double r; explicit CircleAlt(double r_) : r(r_) {} };
struct RectangleAlt { double w, h; RectangleAlt(double w_, double h_) : w(w_), h(h_) {} };
struct TriangleAlt  { double base, height; TriangleAlt(double b, double h) : base(b), height(h) {} };

using GeoShape = std::variant<CircleAlt, RectangleAlt, TriangleAlt>;

struct AreaVisitor {
    double operator()(const CircleAlt&    c) const { return M_PI * c.r * c.r; }
    double operator()(const RectangleAlt& r) const { return r.w * r.h; }
    double operator()(const TriangleAlt&  t) const { return 0.5 * t.base * t.height; }
};

void runVariant() {
    std::cout << "──── 8. std::variant + std::visit ────\n";

    std::vector<GeoShape> shapes = {
        CircleAlt(1.0),
        RectangleAlt(2.0, 3.0),
        TriangleAlt(4.0, 5.0)
    };

    for (const auto& s : shapes) {
        std::cout << "  area = " << std::visit(AreaVisitor{}, s) << "\n";
    }
}


// ──── 9. CRTP — compile-time abstraction ────
// The base is a template; the derived passes itself as the template
// argument. The "virtual call" is resolved at compile time, with no
// vtable and no runtime cost.
template <typename Derived>
class ShapeLike {
public:
    double area() const {
        return static_cast<const Derived*>(this)->areaImpl();
    }
};

class Square : public ShapeLike<Square> {
private:
    double side;
public:
    explicit Square(double s) : side(s) {}
    double areaImpl() const { return side * side; }
};

class TriangleCRTP : public ShapeLike<TriangleCRTP> {
private:
    double base, height;
public:
    TriangleCRTP(double b, double h) : base(b), height(h) {}
    double areaImpl() const { return 0.5 * base * height; }
};

void runCrtp() {
    std::cout << "──── 9. CRTP ────\n";

    Square      sq(2.0);
    TriangleCRTP tr(3.0, 4.0);

    ShapeLike<Square>&      a = sq;
    ShapeLike<TriangleCRTP>& b = tr;

    std::cout << "  sq area = " << a.area()
              << "  tr area = " << b.area() << "\n";
}


int main() {

    // ──── 1. hidden storage ────
    std::cout << "════ 1. hidden storage ════\n";
    runHiddenStorage();


    // ──── 2. abstract interface ────
    std::cout << "\n════ 2. abstract interface ════\n";
    runAbstractInterface();


    // ──── 3. utility class ────
    std::cout << "\n════ 3. utility class ════\n";
    runUtilityClass();


    // ──── 4. interface segregation ────
    std::cout << "\n════ 4. interface segregation ════\n";
    runInterfaceSegregation();


    // ──── 5. factory hides concrete type ────
    std::cout << "\n════ 5. factory hides concrete type ════\n";
    runFactory();


    // ──── 6. template method ────
    std::cout << "\n════ 6. template method ════\n";
    runTemplateMethod();


    // ──── 7. std::function abstraction ────
    std::cout << "\n════ 7. std::function abstraction ════\n";
    runStdFunction();


    // ──── 8. std::variant + std::visit ────
    std::cout << "\n════ 8. std::variant + std::visit ════\n";
    runVariant();


    // ──── 9. CRTP ────
    std::cout << "\n════ 9. CRTP ════\n";
    runCrtp();


    std::cout << "\n════ done ════\n";

    return 0;
}


// ════════════════════════════════════════════════════════════
// End of abstraction demo.
// Companion note: 06-oop-basics/02-abstraction.md
// ════════════════════════════════════════════════════════════