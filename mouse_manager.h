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
    // public slots:
    //  Q_SCRIPTABLE QString messageSlot(const QString&, const QString&);
};
/*
// First, define your QObject which provides the functionality.
class SingletonTypeExample : public QObject {
    Q_OBJECT
    Q_PROPERTY(int someProperty READ someProperty WRITE setSomeProperty NOTIFY cursorShapeChanged)

  public:
    explicit SingletonTypeExample(QObject* parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE int doSomething() {
        setSomeProperty(5);
        return m_someProperty;
    }

    int someProperty() const { return m_someProperty; }
    void setSomeProperty(int val) {
        if (m_someProperty != val) {
            m_someProperty = val;
            emit cursorShapeChanged(val);
        }
    }
  public slots:
    void messageSlot(const QString& a, const QString& b);

  signals:
    void cursorShapeChanged(int new_cursor_shape);

  private:
    int m_someProperty = 0;
};
*/
#endif // MOUSE_MANAGER_H
