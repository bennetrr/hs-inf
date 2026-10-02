package de.hsco.ads.uebung08.tree;

/**
 * Klasse zur Repräsentation einer Position in einem Baum.
 *
 * Letztendlich nur eine Wrapper-Klasse für einen {@link ADsBinaryNode}, da es
 * sich bei {@link ADsBinaryNode} eigentlich um eine interne Klasse handelt.
 */
public class Position {
    ADsBinaryNode node;

    public Position(ADsBinaryNode node) {
		this.node = node;
	}
}
