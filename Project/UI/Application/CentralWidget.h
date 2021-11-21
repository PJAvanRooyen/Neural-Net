#ifndef CentralWidget_H
#define CentralWidget_H

#include "UI/Widget/AbstractWidget.h"

namespace UI {
namespace Application {

class CentralWidget : public AbstractWidget {
  Q_OBJECT

public:
  CentralWidget(QObject *parent = nullptr);
  ~CentralWidget();

protected:
  QWidget *createView(QWidget *parentView) override;

private:
};

} // namespace Application
} // namespace UI
#endif // CentralWidget_H
