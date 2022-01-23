#ifndef Communicator_H
#define Communicator_H

#include <QCoreApplication>
#include <QEvent>
#include <QMetaEnum>
#include <QUuid>
#include <optional>
#include <set>

// test neuralNetInfo
#include "Shared/NeuralNetwork/Defines.h"
// test

namespace Shared {
namespace Communicator {
class IEvent : public QEvent {
public:
  virtual IEvent *copy() const = 0;

protected:
  IEvent(const QEvent::Type eventType) : QEvent(eventType) {}
};

template <class EventType> class Event : public IEvent {
public:
  virtual ~Event() {}

  static QEvent::Type staticType() {
    static QEvent::Type sType =
        static_cast<QEvent::Type>(QEvent::registerEventType());
    return sType;
  }

  IEvent *copy() const {
    return new EventType(*static_cast<const EventType *>(this));
  }

protected:
  Event() : IEvent(staticType()) {}
};

struct EvNeuralNetCreate : public Event<EvNeuralNetCreate> {
  EvNeuralNetCreate(const std::vector<unsigned long> &layerSizes,
                    const QUuid &neuralNetId)
      : Event<EvNeuralNetCreate>(), mLayerSizes(layerSizes),
        mNetId(neuralNetId) {}

  const std::vector<unsigned long> mLayerSizes;

  const QUuid mNetId;
};

struct EvNeuralNetCreateResponse : public Event<EvNeuralNetCreateResponse> {
  EvNeuralNetCreateResponse(const std::optional<QUuid> &neuralNetId)
      : Event<EvNeuralNetCreateResponse>(), mNetId(neuralNetId) {}

  const std::optional<const QUuid> mNetId;
};

struct EvNeuralNetRun : public Event<EvNeuralNetRun> {
  EvNeuralNetRun(const QUuid &neuralNetId)
      : Event<EvNeuralNetRun>(), mNetId(neuralNetId) {}

  const QUuid mNetId;
};

class EvNeuralNetRunInfo : public Event<EvNeuralNetRunInfo> {
public:
  EvNeuralNetRunInfo(const QUuid &neuralNetId,
                     const Shared::NodeNetwork::NeuralNetworkData<double> &data)
      : Event<EvNeuralNetRunInfo>(), mNetId(neuralNetId), mNetData(data) {}

  const QUuid mNetId;

  const Shared::NodeNetwork::NeuralNetworkData<double> mNetData;
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
    if (eventType < QEvent::Type::User) {
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
