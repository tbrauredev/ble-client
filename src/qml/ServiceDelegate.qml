//==============================================================================
// Copyright (C) 2023 Thomas Braure.
//
// This file is part of ble-client.
//
// ble-client is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ble-client is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ble-client. If not, see <https://www.gnu.org/licenses/>.
//==============================================================================

import QtQuick

ServiceDelegateForm {
    id: delegate

    property bool expanded: false

    signal pressed()
    signal released()
    signal clicked()

    state: expanded ? "expanded" : "collapsed"
    itemDelegate.text: name
    uuidLabel.text: uuid

    states: [
        State {
            name: "expanded"

            PropertyChanges {
                target: mouseArea
                enabled: true
                hoverEnabled: true
            }

            PropertyChanges {
                target: detailsPane
                opacity: 1.0
            }

            PropertyChanges {
                target: detailsPane
                visible: true
            }

            PropertyChanges {
                target: delegate
                contentHeight: itemDelegate.height + detailsPane.height
            }
        },

        State {
            name: "collapsed"

            PropertyChanges {
                target: mouseArea
                enabled: false
                hoverEnabled: false
            }

            PropertyChanges {
                target: detailsPane
                opacity: 0.0
            }

            PropertyChanges {
                target: detailsPane
                visible: false
            }

            PropertyChanges {
                target: delegate
                contentHeight: itemDelegate.height
            }
        }
    ]

    transitions: [
        Transition {
            to: "expanded"

            SequentialAnimation {
                PropertyAnimation {
                    target: delegate
                    property: "contentHeight"
                    easing.type: Easing.InOutQuad
                }

                PropertyAnimation {
                    target: detailsPane
                    property: "opacity"
                    easing.type: Easing.InOutQuad
                    duration: 100
                }
            }
        },

        Transition {
            to: "collapsed"

            PropertyAnimation {
                target: delegate
                property: "contentHeight"
                easing.type: Easing.InOutQuad
            }
        }
    ]

    Connections {
        target: itemDelegate

        function onPressed() {
            delegate.pressed();
        }

        function onReleased() {
            delegate.released();
        }

        function onClicked() {
            delegate.clicked();
        }
    }
}
