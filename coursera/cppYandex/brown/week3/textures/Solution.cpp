#include <functional>
#include <iostream>

#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

class Rectangle : public IShape {
 public:
  Rectangle() : position_({0, 0}), size_({0, 0}) {}

  // Возвращает точную копию фигуры.
  // Если фигура содержит текстуру, то созданная копия содержит ту же самую
  // текстуру. Фигура и её копия совместно владеют этой текстурой.
  std::unique_ptr<IShape> Clone() const {
    return make_unique<Rectangle>(*this);
  };

  void SetPosition(Point pos) { position_ = pos; };
  Point GetPosition() const { return position_; };

  void SetSize(Size sz) { size_ = sz; }
  Size GetSize() const { return size_; };

  void SetTexture(std::shared_ptr<ITexture> texture) { texture_ = texture; }
  ITexture* GetTexture() const { return texture_.get(); }

  // Рисует фигуру на указанном изображении
  void Draw(Image& img) const {
    DrawImage(img, *this, [](Point p, Size s) { return true; });
  }

 private:
  Point position_;
  Size size_;
  std::shared_ptr<ITexture> texture_;
  friend void DrawImage(Image& img, const IShape&, function<bool(Point, Size)>);
};

class Ellipse : public IShape {
 public:
  Ellipse() : position_({0, 0}), size_({0, 0}) {}

  // Возвращает точную копию фигуры.
  // Если фигура содержит текстуру, то созданная копия содержит ту же самую
  // текстуру. Фигура и её копия совместно владеют этой текстурой.
  std::unique_ptr<IShape> Clone() const { return make_unique<Ellipse>(*this); };

  void SetPosition(Point pos) { position_ = pos; };
  Point GetPosition() const { return position_; };

  void SetSize(Size sz) { size_ = sz; }
  Size GetSize() const { return size_; };

  void SetTexture(std::shared_ptr<ITexture> texture) { texture_ = texture; }
  ITexture* GetTexture() const { return texture_.get(); }

  // Рисует фигуру на указанном изображении
  void Draw(Image& img) const {
    DrawImage(img, *this, IsPointInEllipse);
  }

 private:
  Point position_;
  Size size_;
  std::shared_ptr<ITexture> texture_;
  friend void DrawImage(Image& img, const IShape&, function<bool(Point, Size)>);
};

void DrawImage(Image& img, const IShape& shape,
               function<bool(Point, Size)> func) {
  Point position = shape.GetPosition();
  Size size = shape.GetSize();
  ITexture* ptexture = shape.GetTexture();

  int x_start = min(position.x, (int)img[0].size());
  int x_end = min(x_start + size.width, (int)img[0].size());
  int y_start = min(position.y, (int)img.size());
  int y_end = min(y_start + size.height, (int)img.size());
  for (int x = x_start; x < x_end; x++) {
    for (int y = y_start; y < y_end; y++) {
      if (func({x - x_start, y - y_start}, size)) {
        img[y][x] = '.';
      }
    }
  }
  if (ptexture) {
    Size tsize = ptexture->GetSize();
    const Image& texture = ptexture->GetImage();
    x_end = min(x_start + tsize.width, x_end);
    y_end = min(y_start + tsize.height, y_end);
    for (int x = x_start, xt_start = 0; x < x_end; x++, xt_start++) {
      for (int y = y_start, yt_start = 0; y < y_end; y++, yt_start++) {
        if (func({x - x_start, y - y_start}, size)) {
          img[y][x] = texture[yt_start][xt_start];
        }
      }
    }
  }
}

// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {
  switch (shape_type) {
    case ShapeType::Rectangle:
      return make_unique<Rectangle>();
      break;
    case ShapeType::Ellipse:
      return make_unique<Ellipse>();
      break;
    default:
      break;
  }
  return nullptr;
}