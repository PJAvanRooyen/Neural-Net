#ifndef Communicator_H
#define Communicator_H

#include <QCoreApplication>
#include <QEvent>
#include <QUuid>
#include <optional>
#include <set>

namespace Shared {
namespace Communicator {
class IEvent : public QEvent {
public:
  virtual IEvent *copy() const = 0;

protected:
  IEvent(const QEvent::Type eventType) : QEvent(eventType) {}
};

template <class EventType> class AbstractEvent : public IEvent {
public:
protected:
  AbstractEvent()
      : IEvent(static_cast<QEvent::Type>(QEvent::registerEventType())) {}

  IEvent *copy() const {
    return new EventType(*static_cast<const EventType *>(this));
  }
};

struct EvNeuralNetCreate : public AbstractEvent<EvNeuralNetCreate> {
  EvNeuralNetCreate(const std::vector<unsigned long> &layerSizes)
      : AbstractEvent<EvNeuralNetCreate>(), mLayerSizes(layerSizes) {}

  const std::vector<unsigned long> mLayerSizes;
};

struct EvNeuralNetCreateResponse
    : public AbstractEvent<EvNeuralNetCreateResponse> {
  EvNeuralNetCreateResponse(const std::optional<QUuid> &neuralNetId)
      : AbstractEvent<EvNeuralNetCreateResponse>(), mNetId(neuralNetId) {}

  const std::optional<const QUuid> mNetId;
};

struct EvNeuralNetRun : public AbstractEvent<EvNeuralNetRun> {
  EvNeuralNetRun(const QUuid &neuralNetId)
      : AbstractEvent<EvNeuralNetRun>(), mNetId(neuralNetId) {}

  const QUuid mNetId;
};

class EvNeuralNetRunInfo : public AbstractEvent<EvNeuralNetRunInfo> {
public:
  EvNeuralNetRunInfo(const QUuid &neuralNetId)
      : AbstractEvent<EvNeuralNetRunInfo>(), mNetId(neuralNetId) {}

  const QUuid mNetId;
};

class Communicator {
public:
  ~Communicator() {}

  static Communicator &instance() {
    static Communicator instance;
    return instance;
  }

  void connect(QObject *const receiver,
               const std::vector<IEvent::Type> &events) {
    for (IEvent::Type eventType : events) {
      auto &eventReceivers = mReceivers[eventType];
      eventReceivers.insert(receiver);
    }
  }

  void postEvent(const IEvent *const event) const {
    const IEvent::Type eventType = event->type();
    if (eventType != IEvent::Type::User) {
      return;
    }

    const std::set<QObject *> &eventReceivers = mReceivers.at(eventType);
    for (QObject *const receiver : eventReceivers) {
      QCoreApplication::postEvent(receiver, event->copy());
    }
  }
  // TODO: broadcast connect; create objectTypes as we have eventTypes, when
  // sending broadcast events, they are sent to all objects of a type instead
  // of a unique object.

private:
  Communicator() : mReceivers() {}

  std::map<const IEvent::Type, std::set<QObject *>> mReceivers;
};

} // namespace Communicator
} // namespace Shared

#endif // Communicator_H
