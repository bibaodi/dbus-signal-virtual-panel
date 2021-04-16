#ifndef MOUSE_MANAGER_H
#define MOUSE_MANAGER_H

#include <QObject>
#include <QQuickItem>

class Mouse_Manager : public QObject {
    Q_OBJECT
  public:
    Mouse_Manager();
};

class MouseMgr_CursorShapeArea : public QQuickItem {
    Q_OBJECT
    Q_PROPERTY(int cursor_Shape READ cursor_Shape WRITE set_CursorShape NOTIFY cursorShapeChanged)
  public:
    explicit MouseMgr_CursorShapeArea(QQuickItem* parent = 0);
    static MouseMgr_CursorShapeArea* get_instance();

    int cursor_Shape() const;
    Q_INVOKABLE void set_CursorShape(int cursorShape);

  private:
    int m_currentShape;
    MouseMgr_CursorShapeArea* m_instance;

  signals:
    void cursorShapeChanged();
};
#endif // MOUSE_MANAGER_H
